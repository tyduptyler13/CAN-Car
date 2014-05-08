{
	"targets": [
		{
			"target_name": "CNI",
			"sources": [
				"CANInterface.cpp"
			],
			'include_dirs': [
				'./INC'
			],
			"conditions": [
				[ "target_arch=='ia32'" , {
					"link_settings": {
						"libraries": [
							'-l../Lib/MS/canlib32.lib'
						]
					}
				}],
				[ "target_arch=='x64'" , {
					"link_settings": {
						"libraries": [
							"-l../Lib/x64/canlib32.lib"
						]
					}
				}]
			]
		}
	]
}
