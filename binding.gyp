{
    "targets": [
        {
            "target_name": "zip",
            "sources": [
                "src/zip.cc"
            ],
            "include_dirs": [
                "<!(node -e \"require('nan')\")"
            ]
        }
    ]
}
