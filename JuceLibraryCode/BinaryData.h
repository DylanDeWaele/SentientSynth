/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   _12brainfreepngimage_800x800_png;
    const int            _12brainfreepngimage_800x800_pngSize = 212186;

    extern const char*   SuperBrigade2O8Ao_otf;
    const int            SuperBrigade2O8Ao_otfSize = 36712;

    extern const char*   PluginBackground_jpg;
    const int            PluginBackground_jpgSize = 193620;

    extern const char*   Readme_txt;
    const int            Readme_txtSize = 269;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 4;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
