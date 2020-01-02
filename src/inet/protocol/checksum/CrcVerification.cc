//
// Copyright (C) OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see http://www.gnu.org/licenses/.
//

#include "inet/common/checksum/TcpIpChecksum.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/protocol/checksum/CrcHeader_m.h"
#include "inet/protocol/checksum/CrcVerification.h"
#include "inet/protocol/IProtocol.h"

namespace inet {

Define_Module(CrcVerification);

void CrcVerification::initialize(int stage)
{
    PacketFilterBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        crcMode = parseCrcMode(par("crcMode"), true);
        registerService(IProtocol::crc, nullptr, inputGate);
        registerProtocol(IProtocol::crc, nullptr, outputGate);
    }
}

bool CrcVerification::matchesPacket(Packet *packet)
{
    Ptr<const CrcHeader> header;
    if (!strcmp(par("headerPosition"), "front"))
        header = packet->popAtFront<CrcHeader>();
    else if (!strcmp(par("headerPosition"), "back"))
        header = packet->popAtBack<CrcHeader>(B(2));
    else
        throw cRuntimeError("Unknown headerPosition parameter value");
    const auto& data = packet->peekDataAsBytes();
    switch (header->getCrcMode()) {
        case CRC_DISABLED:
            // if the CRC mode is disabled, then the check passes if the CRC is 0
            return header->getCrc() == 0x0000;
        case CRC_DECLARED_CORRECT: {
            // if the CRC mode is declared to be correct, then the check passes if and only if the chunks are correct
            return header->isCorrect() && data->isCorrect();
        }
        case CRC_DECLARED_INCORRECT:
            // if the CRC mode is declared to be incorrect, then the check fails
            return false;
        case CRC_COMPUTED: {
            if (header->getCrc() == 0x0000)
                // if the CRC mode is computed and the CRC is 0 (disabled), then the check passes
                return true;
            else {
                // otherwise compute the CRC, the check passes if the result is 0xFFFF (includes the received CRC) and the chunks are correct
                auto receivedCrc = header->getCrc();
                auto computedCrc = TcpIpChecksum::checksum(data->getBytes());
                return receivedCrc == computedCrc;
            }
        }
        default:
            throw cRuntimeError("Unknown CRC mode");
    }
}

} // namespace inet

