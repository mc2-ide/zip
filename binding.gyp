{
    "targets": [
        {
            "target_name": "addon",
            "sources": [
                "src/zip.cc"
            ],
            "include_dirs": [
                "<!(node -e \"require('nan')\")"
            ]
        }
    ]
}
