exploitee.rs Meshtastic packet dissector for Wireshark
hackerpager.net
======================================================


# Installation Instructions

Please make sure to follow all the steps or you will see a lot of errors.

1. Copy the meshtastic/ directory to the plugins/ directory of Wireshark's "personal configuration folder".
  * The location of this folder varies by system: https://www.wireshark.org/docs/wsug_html_chunked/ChAppFilesConfigurationSection.html
  * You may need to create a plugins/ subdirectory in this folder if it doesn't already exist.
  * On Windows, this will look like: C:\Users\YOUR_USERNAME\AppData\Roaming\Wireshark\plugins\meshtastic
  * On Mac, /Users/YOUR_USERNAME/.config/wireshark/plugins/meshtastic

2. Open Wireshark.

3. Open Edit > Preferences > Protocols > ProtoBuf

4. Check "Load .proto files on startup."

5. Check "Dissect protobuf fields as Wireshark fields."

6. Click "Edit..." next to "Protobuf search paths".

7. Add the plugins/meshtastic/protobufs/ directory.

8. Check "Load all files" next to new entry.

9. Save and close preferences.


# Setting the Channel Encryption Key (required)

1. Open Edit > Preferences > Protocols > Meshtastic

2. Enter the channel encryption key in base64 format.

3. Save changes and restart Wireshark.

The easiest way to find your channel encryption key is by pairing the Pager with the Meshtastic phone app,
then reading the key from the radio configuration menu in the app.
  * The key for the default Meshtastic channel (a.k.a. "LongFast") is: AQ==
  * The key for the "DEFCONnect" DEF CON event channel is: OEu8wB3AItGBvza4YSHh+5a3LlW/dCJ+nWr7SNZMsaE=

If a packet can't be decrypted (because it's corrupted or was encrypted with a different key), it will be shown as a 
"Malformed meshtastic.Data protobuf" error in the Wireshark UI.


All set! Restart Wireshark and open your .pcap file.