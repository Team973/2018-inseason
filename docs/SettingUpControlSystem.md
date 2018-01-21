# Setting Up Control System

### Roborio
- Open the Roborio Imaging Tool
- Wait until the Imaging tool finds the roboRIO target
- Once it finds the roborio, type in `973` in the
- Check format target option
- Select the newest image available
- Click Reformat

### Talon and Victor Addressing
- Go to the Silverlight Web UI at `roborio-973-frc.local` or IP address assigned after imaging the rio
- Install Phoenix lifeboat. Follow the instructions in the program for Installing Phoenix/Web-based Config
- Once it is done installing, there will be a list of available Talons and Victors for addressing
- For each talon/victor, rename each talon to its specific purpose like `Left Drive Talon A Master`, and reindex each to its own specific ID. Refer to the wiring IO spreadsheet for the up-to-date list of which IDs to index each talon/victor.
- You might have to restart every time you index each talon/victor since new talons/victors default to ID 0.
- Update the firmware for each talon and victor to the newest version. It is available at CTRE’s website.
