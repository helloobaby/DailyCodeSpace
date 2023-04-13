/*
用法 DisplayError(HRESULT_FROM_WIN32(GetLastError()));
如果在中文环境可能需要
std::locale::global(locale(""));
*/
#include <strsafe.h>
#include <windows.h>

VOID
DisplayError (
   _In_ DWORD Code
   )

/*++

Routine Description:

   This routine will display an error message based off of the Win32 error
   code that is passed in. This allows the user to see an understandable
   error message instead of just the code.

Arguments:

   Code - The error code to be translated.

Return Value:

   None.

--*/

{
    _Null_terminated_ WCHAR buffer[MAX_PATH] = { 0 }; 
    DWORD count;
    HMODULE module = NULL;
    HRESULT status;

    count = FormatMessage (FORMAT_MESSAGE_FROM_SYSTEM,
                           NULL,
                           Code,
                           0,
                           buffer,
                           sizeof(buffer) / sizeof(WCHAR),
                           NULL);


    if (count == 0) {

        count = GetSystemDirectory( buffer,
                                    sizeof(buffer) / sizeof( WCHAR ) );

        if (count==0 || count > sizeof(buffer) / sizeof( WCHAR )) {

            //
            //  In practice we expect buffer to be large enough to hold the 
            //  system directory path. 
            //

            printf("    Could not translate error: %u\n", Code);
            return;
        }


        status = StringCchCat( buffer,
                               sizeof(buffer) / sizeof( WCHAR ),
                               L"\\fltlib.dll" );

        if (status != S_OK) {

            printf("    Could not translate error: %u\n", Code);
            return;
        }

        module = LoadLibraryExW( buffer, NULL, LOAD_LIBRARY_AS_DATAFILE );

        //
        //  Translate the Win32 error code into a useful message.
        //

        count = FormatMessage (FORMAT_MESSAGE_FROM_HMODULE,
                               module,
                               Code,
                               0,
                               buffer,
                               sizeof(buffer) / sizeof(WCHAR),
                               NULL);

        if (module != NULL) {

            FreeLibrary( module );
        }

        //
        //  If we still couldn't resolve the message, generate a string
        //

        if (count == 0) {

            printf("    Could not translate error: %u\n", Code);
            return;
        }
    }

    //
    //  Display the translated error.
    //

    printf("%ws\n", buffer);
}