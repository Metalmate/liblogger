file(REMOVE_RECURSE
  "liblogger.pdb"
  "liblogger.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/logger.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
