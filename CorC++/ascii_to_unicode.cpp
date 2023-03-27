std::wstring toUtf16(std::string const & str)
{
    std::wstring RetVal;

    int SizeReq = MultiByteToWideChar(
        CP_ACP,
        0,
        str.c_str(),
        -1,
        NULL,
        0
        );
    if ( SizeReq )
    {
        std::vector<wchar_t> Buffer(SizeReq);
        SizeReq = MultiByteToWideChar(
            CP_ACP,
            0,
            str.c_str(),
            -1,
            &Buffer[0],
            SizeReq
            );
        if ( SizeReq )
        {
            RetVal = &Buffer[0];
        }
    }
    return RetVal;
}