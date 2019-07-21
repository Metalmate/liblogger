file(REMOVE_RECURSE
  "liblogger_shared.pdb"
  "liblogger_shared.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/logger_shared.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
