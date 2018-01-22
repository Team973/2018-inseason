# Setting Up Control System

### Roborio
- Open the Roborio Imaging Tool
- Wait until the Imaging tool finds the roboRIO target
- Once it finds the roborio, type in `973` in the
- Check format target option
- Select the newest image available
- Click Reformat

### Talon and Victor Addressing
- Go to the Silverlight Web UI at `roborio-973-frc.local` or IP address assigned after imaging the rio. If you are using the programming laptops, use Internet Explorer or Mozilla Firefox.
- Install [Phoenix lifeboat](http://www.ctr-electronics.com/control-system/hro.html#product_tabs_technical_resources). Follow the instructions in the program for Installing Phoenix/Web-based Config and use a USB A to USB B cable (printer cable).
- Once it is done installing, there will be a list of available Talons and Victors for addressing
- For each talon/victor, rename each talon to its specific purpose like `Left Drive Talon A Master`, and reindex each to its own specific ID. Refer to the wiring IO spreadsheet for the up-to-date list of which IDs to index each talon/victor.
- You might have to restart every time you index each talon/victor since new talons/victors default to ID 0.
- Update the FRC-specific firmware for each [talon](http://www.ctr-electronics.com/talon-srx.html#product_tabs_technical_resources) and [victor](http://www.ctr-electronics.com/victor-spx.html#product_tabs_technical_resources) to the newest version.
