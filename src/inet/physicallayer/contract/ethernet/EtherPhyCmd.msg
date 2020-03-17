//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

import inet.physicallayer.ieee80211.mode.IIeee80211Mode;
import inet.physicallayer.ieee80211.mode.Ieee80211Channel;

cplusplus {{
}}

namespace inet::physicallayer;

enum EtherPhyCommand {
        CMD_SEND = 101;                         // send SFD; error, ha van küldés folyamatban
        CMD_SEND_EXPRESS = 102;                 // send SMD-E; error, ha van küldés folyamatban
        CMD_SEND_PREEMPTABLE = 103;             // send SMD-Sx; error, ha van küldés folyamatban
        CMD_MODIFY_CURRENT_PREEMPTABLE = 104;   // módosítja az éppen küldés alatt álló csomagot
                                                // error, ha a megadott bit offset változási pozíción már túljutott a küldés vagy ha nincs küldés folyamatban
                                                // param: offset of first changed byte
        CMD_SEND_CONTINUED_PREEMPTABLE = 105;   // send SMD-Cx, a folytatás csomag küldése,
                                                // param: Frag Count
                                                // error, ha van küldés folyamatban
        // CMD_SEND_JAM,
        // CMD_SEND_FILLED_IFG,
};

class PreemptableModifierCtrlInfo extends cObject
{
    B firstChangedOffset;
};

class PreemptableFragmentCtrlInfo extends cObject
{
    int fragCount;
}

