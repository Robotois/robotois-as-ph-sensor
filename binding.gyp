{
  "targets": [
    {
      "target_name": "PhSensor",
      "sources": [
        "src/lib/wrapper/PhSensor.cpp",
        "src/lib/wrapper/PhWrapper.cpp",
        "src/lib/PhSensor/PhSensor.cpp",
      ],
      "libraries": ["-l bcm2835", "-l rt"],
      "cflags_cc": ['-fexceptions']
    }
  ]
}
