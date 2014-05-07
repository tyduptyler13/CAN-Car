{
	"targets": [
		{
			"target_name": "CANInterface",
			"sources": [ "CANInterface.cpp" ]
		}
	],
	"conditions": [
		['OS=="win"', {
			'include_dirs': [],
			'libraries': []
		}]
	]
}
