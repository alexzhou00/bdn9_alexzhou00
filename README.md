# bdn9_alexzhou00
keymap for BDN9 Rev. 2

## Installation
Just clone this into ```qmk_firmware/keyboards/keebio/bdn9/keymaps/bdn9_alexzhou00```

Then, you should be able to compile and upload this to any BDN9 Rev. 2 using ```qmk flash -kb keebio/bdn9/rev2 -km bdn9_alexzhou00```. Note that you have to hit the reset button on your PCB before you can flash your board.

For muting/unmuting, you can take the AutoHotkey V2 scripts from here: https://github.com/alexzhou00/ahk/tree/main. Note that these do not work with AutoHotkey V1 (the default installation at time of writing \[4/1/2021\]).

For use with YeeLight lightbulbs, see https://github.com/alexzhou00/YeeLightGroupControl.

## Middle Layer CAD model

This was made for putting in between the two FR4 plates, since at the time none of the middle acrylic layers were available from Keebio.

I really didn't like how the PCB would flex whenever I clicked the encoders, since the encoders are not supported by the FR4 plate (the key switches mount to the plate, the solder joints for the switches support the PCB, and the encoders are mounted on the PCB). So, I had a friend 3D print a middle piece for me that both supports the PCB and acts as a diffuser.

Fusion 360 link: https://a360.co/3fzCd8A

Full disclosure: This is the first 3D model I've ever made for 3D printing. The tolerances should be fine, although it wouldn't hurt for you to double check yourself, especially for the thickness of the bottom. I designed it for roughly .4mm tolerances, as this was 3D printed on a Creality Ender 3.

## Documentation
Keymapping: https://docs.google.com/spreadsheets/d/113ezfiWuT76fybsH2GwZeazhtU_OuRjdXRp3At457Ek/edit#gid=0

## TODO
* Update keymap comments in C code.
