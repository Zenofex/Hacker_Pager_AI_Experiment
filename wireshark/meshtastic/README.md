# Installation Instructions

1. Copy the meshtastic/ directory to the plugins/ directory of your "personal configuration folder".
  See: https://www.wireshark.org/docs/wsug_html_chunked/ChAppFilesConfigurationSection.html
  (you may need to create the plugins/ directory)
  E.g. C:\Users\Dade\AppData\Roaming\Wireshark\plugins\meshtastic
2. Open Wireshark.
3. Open Edit > Preferences > Protocols > ProtoBuf
4. Check "Load .proto files on startup."
5. Check "Dissect protobuf fields as Wireshark fields."
6. Click "Edit..." next to "Protobuf search paths".
7. Add the plugins/meshtastic/protobuf/ directory.
8. Check "Load all files" next to new entry.
9. Save and close preferences.
10. Open .pcap file.

# Optional packet coloring rules
1. View > Coloring Rules...
2. Import...
3. Select plugins/meshtastic/colorrules
