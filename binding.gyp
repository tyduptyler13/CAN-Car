{
	"targets": [
		{
			"target_name": "CNI",
			"sources": [
				"CANInterface.cpp"
			],
			"conditions": [
				[ "OS=='win'" , {
					"include_dirs": [
						'./windows/INC'
					],
					"conditions": [
						[ "target_arch=='ia32'" , {
							"link_settings": {
								"libraries": [
									'-l../windows/Lib/MS/canlib32.lib'
								]
							}
						}],
						[ "target_arch=='x64'" , {
							"link_settings": {
								"libraries": [
									"-l../windows/Lib/x64/canlib32.lib"
								]
							}
						}]
					]
				}],
				[ "OS=='linux'" , {
					"include_dirs": [
						'./linux/include/'
					],
					"cflags": [
						"-std=c++11",
						"-Wall",
						"-O3"
					],
					"link_settings": {
						"libraries": [
							'../linux/lib/libcanlib.so'
						]
					}
				}]
			]
		}
	]
}
