asm(R"(
        // make invalid type errors make sense
	.section h0; .set h0,0xD459B0; .string "%s expected but got %s\0\0"; // from `attempt to %s a %s value`
	.section h1; .set h1,0xD44F60; .string "userdata\0\0\0\0\0\0\0";     // from `use as userdata`
	.section h2; .set h2,0xE00AD0; .string "string\0\0\0\0\0\0\0";       // from `use as string`
	.section h3; .set h3,0xE00AE0; .string "boolean\0\0\0\0\0\0\0";      // from `use as boolean`
	.section h4; .set h4,0xE01168; .string "integer\0\0\0\0\0\0\0";      // from `use as integer`
	.section h5; .set h5,0xE09310; .string "thread\0\0\0\0\0\0\0";       // from `use as thread`
	.section h6; .set h6,0xE09A50; .string "number\0\0\0\0\0\0\0";       // from `use as number`
        // make logging functions separate arguments with the tab
	.section h7; .set h7,0xE09AEC; .string "\t\0\0\0\0";                 // from `\%03o`
)");