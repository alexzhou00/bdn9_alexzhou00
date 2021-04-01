# bdn9_alexzhou00
keymap for BDN9

Just clone this into ```qmk_firmware/keyboards/keebio/bdn9/keymaps/bdn9_alexzhou00```

Then, you should be able to compile and upload this to any BDN9 Rev. 2 using ```qmk flash -kb keebio/bdn9/rev2 -km bdn9_alexzhou00```. Note that you have to hit the reset button on your PCB before you can flash your board.

For muting/unmuting, you can take the AutoHotkey V2 scripts from here: https://github.com/alexzhou00/ahk/tree/main. Note that these do not work with AutoHotkey V1 (the default installation at time of writing \[4/1/2021\]).

For use with YeeLight lightbulbs, see https://github.com/alexzhou00/YeeLightGroupControl.

## Documentation
Keymapping: https://docs.google.com/spreadsheets/d/113ezfiWuT76fybsH2GwZeazhtU_OuRjdXRp3At457Ek/edit#gid=0

## TODO
* Update keymap comments in C code.
