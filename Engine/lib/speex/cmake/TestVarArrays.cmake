include(CheckCSourceCompiles)

macro(TEST_VARARRAYS VARIABLE)
	if(NOT DEFINED ${VARIABLE})
		check_c_source_compiles(
			"
			void main(void)
			{
				int foo;
				foo = 10;
				int array[foo];
			};
			"
			VARARRAYS_SUPPORT)
		set(${VARIABLE} ${VARARRAYS_SUPPORT} CACHE INTERNAL "C99 variable-size arrays support" FORCE)
		if(${VARIABLE})
			set(RESULT_TEXT "success")
		else()
			set(RESULT_TEXT "failed")
		endif()
	endif()
endmacro(TEST_VARARRAYS VARIABLE)
