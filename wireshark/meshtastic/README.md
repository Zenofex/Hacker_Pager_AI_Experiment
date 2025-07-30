# Installation Instructions

1. Copy the meshtastic/ directory to the plugins/ directory of Wireshark's "personal configuration folder".
  * The location of this folder varies by system: https://www.wireshark.org/docs/wsug_html_chunked/ChAppFilesConfigurationSection.html
  * You may need to create the plugins/ directory if it doesn't already exist.
  * On Windows, this will look something like: C:\Users\YOUR_USERNAME\AppData\Roaming\Wireshark\plugins\meshtastic

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
