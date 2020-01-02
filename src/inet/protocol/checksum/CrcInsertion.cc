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
#include "inet/common/ProtocolTag_m.h"
#include "inet/protocol/checksum/CrcHeader_m.h"
#include "inet/protocol/checksum/CrcInsertion.h"
#include "inet/protocol/IProtocol.h"

namespace inet {

Define_Module(CrcInsertion);

void CrcInsertion::initialize(int stage)
{
    PacketFlowBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        crcMode = parseCrcMode(par("crcMode"), true);
        registerService(IProtocol::crc, inputGate, nullptr);
        registerProtocol(IProtocol::crc, outputGate, nullptr);
    }
}

void CrcInsertion::processPacket(Packet *packet)
{
    const auto& header = makeShared<CrcHeader>();
    header->setCrcMode(crcMode);
    switch (crcMode) {
        case CRC_DISABLED:
            // if the CRC mode is disabled, then the CRC is 0
            header->setCrc(0x0000);
            break;
        case CRC_DECLARED_CORRECT:
            // if the CRC mode is declared to be correct, then set the CRC to an easily recognizable value
            header->setCrc(0xC00D);
            break;
        case CRC_DECLARED_INCORRECT:
            // if the CRC mode is declared to be incorrect, then set the CRC to an easily recognizable value
            header->setCrc(0xBAAD);
            break;
        case CRC_COMPUTED: {
            // if the CRC mode is computed, then compute the CRC and set it
            auto data = packet->peekDataAsBytes();
            uint16_t crc = TcpIpChecksum::checksum(data->getBytes());
            header->setCrc(crc);
            break;
        }
        default:
            throw cRuntimeError("Unknown CRC mode: %d", (int)crcMode);
    }
    if (!strcmp(par("headerPosition"), "front"))
        packet->insertAtFront(header);
    else if (!strcmp(par("headerPosition"), "back"))
        packet->insertAtBack(header);
    else
        throw cRuntimeError("Unknown headerPosition parameter value");
    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&IProtocol::crc);
}

} // namespace inet

