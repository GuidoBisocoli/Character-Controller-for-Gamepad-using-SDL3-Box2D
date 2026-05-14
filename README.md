## A character controller for gamepads using SDL3 and Box2D v3

https://github.com/user-attachments/assets/ededbe5e-ee0e-49f1-a946-9f379530b579

# Usage
- Create an empty Solution in Visual Studio and add the code
- Download SDL3, Box2D, and SDL_Image, unzip them to separate folders
- Open Project properties and add
  - to C/C++ -> General -> Additional Include Directories:
    - $(ProjectDir)hdr, ...\SDL3\include, ...\SDL3_image-3.y.z\include and ...\box2d-3.y.z\include
  - to Linker -> General -> Additional Library Directories:
    - ...\SDL3\VisualC\$(PlatformTarget)\$(Configuration), ...\SDL3_image-3.y.z\lib\$(PlatformTarget) and ...\box2d-3.y.z\build\src\$(Configuration)
  - to Linker -> Input -> Additional Dependencies:
    - SDL3.lib, SDL3_image.lib and box2d[d].lib
- Compile and copy SDL3.dll and SDL3_image.dll to the created folder (for example: x64\Release\)

# Download
- Download from [releases](https://github.com/GuidoBisocoli/Character-Controller-for-Gamepad-using-SDL3-Box2D/releases/tag/v1.0) if you just want to test it

# Controls (with Gamepad):
- Left Stick: move the character
- A (on XInput): tap the ball
- X (on XInput): kick the ball with medium strength
- B (on XInput): kick the ball with max strength
- Right Shoulder: run
- D on the keyboard: toggle debug draw

