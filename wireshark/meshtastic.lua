-- Copy to the plugins/ directory of your "personal configuration folder:
-- https://www.wireshark.org/docs/wsug_html_chunked/ChAppFilesConfigurationSection.html
-- (you may need to create the plugins/ directory)
-- E.g. C:\Users\Dade\AppData\Roaming\Wireshark\plugins

local info = {
    version = "1.0",
    author = "exploitee.rs",
}
set_plugin_info(info)


local proto_meshtastic = Proto.new("meshtastic", "Meshtastic");

local f_to = ProtoField.uint32("meshtastic.to", "Destination node", base.HEX);
local f_from = ProtoField.uint32("meshtastic.from", "Sender node", base.HEX);
local f_id = ProtoField.uint32("meshtastic.id", "Packet ID", base.HEX);
local f_flags = ProtoField.uint8("meshtastic.flags", "Flags", base.HEX);
local f_hop_limit = ProtoField.uint8("meshtastic.flags.hop_limit", "Hop limit (remaining hops)", base.DEC, nil, 0x07);
local f_hop_start = ProtoField.uint8("meshtastic.flags.hop_start", "Hop limit (original)", base.DEC, nil, 0xE0);
local f_want_ack = ProtoField.bool("meshtastic.flags.want_ack", "ACK requested", 8, nil, 0x08);
local f_via_mqtt = ProtoField.bool("meshtastic.flags.via_mqtt", "Path included MQTT", 8, nil, 0x10);
local f_channel = ProtoField.uint8("meshtastic.channel_hash", "Channel hash", base.HEX);
local f_next_hop = ProtoField.uint8("meshtastic.next_hop", "Next hop node (unused)", base.HEX);
local f_relay_node = ProtoField.uint8("meshtastic.relay_node", "Relay node (unused)", base.HEX);
local f_payload = ProtoField.bytes("meshtastic.payload", "Payload", base.NONE);

proto_meshtastic.fields = { 
    f_to,
    f_from,
    f_id,
    f_flags,
    f_hop_limit,
    f_hop_start,
    f_want_ack,
    f_via_mqtt,
    f_channel,
    f_next_hop,
    f_relay_node,
    f_payload,
};

function proto_meshtastic.dissector(tvb, pinfo, treeitem)
    local subtree = treeitem:add(proto_meshtastic, tvb());
    local pos = 0;

    subtree:add_le(f_to, tvb(pos, 4));
    pos = pos + 4;

    subtree:add_le(f_from, tvb(pos, 4));
    pos = pos + 4;

    subtree:add_le(f_id, tvb(pos, 4));
    pos = pos + 4;

    local flags = subtree:add(f_flags, tvb(pos, 1))
    flags:add(f_hop_limit, tvb(pos, 1));
    flags:add(f_hop_start, tvb(pos, 1));
    flags:add(f_want_ack, tvb(pos, 1));
    flags:add(f_via_mqtt, tvb(pos, 1));
    pos = pos + 1;

    subtree:add(f_channel, tvb(pos, 1));
    pos = pos + 1;

    subtree:add(f_next_hop, tvb(pos, 1));
    pos = pos + 1;

    subtree:add(f_relay_node, tvb(pos, 1));
    pos = pos + 1;

    local payload = subtree:add(f_payload, tvb(pos));

end

local loratap_table = DissectorTable.get("loratap.syncword");
loratap_table:add(0x2b, proto_meshtastic);
