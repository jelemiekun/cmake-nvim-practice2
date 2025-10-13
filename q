[1mdiff --git a/source/CMakeLists.txt b/source/CMakeLists.txt[m
[1mindex df2fee6..d09f824 100644[m
[1m--- a/source/CMakeLists.txt[m
[1m+++ b/source/CMakeLists.txt[m
[36m@@ -37,3 +37,11 @@[m [mif (EXISTS main.cpp)[m
 else()[m
   message("main.cpp does not exist!")[m
 endif()[m
[32m+[m
[32m+[m[32madd_subdirectory(game)[m
[32m+[m
[32m+[m[32mif (TARGET s_Game)[m
[32m+[m[32m  message("s_Game is defined")[m
[32m+[m[32melse()[m
[32m+[m[32m  message("s_Game not defined")[m
[32m+[m[32mendif()[m
