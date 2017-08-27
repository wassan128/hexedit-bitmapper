--- hexedit.h.orig	2008-11-08 00:50:57.000000000 +0900
+++ hexedit.h	2015-06-17 20:35:54.000000000 +0900
@@ -5,6 +5,7 @@
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
+#include <sys/param.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #if HAVE_FCNTL_H
@@ -70,6 +71,17 @@
 extern modeParams modes[LAST];
 extern modeType mode;
 extern int colored;
+#ifdef HAVE_COLORS
+extern int color_null_fg;
+extern int color_control_fg;
+extern int color_extended_fg;
+extern int color_normal_fg;
+extern int color_null_bg;
+extern int color_control_bg;
+extern int color_extended_bg;
+extern int color_normal_bg;
+extern int bold;
+#endif
 extern char *usage;
 
 #define pressAnyKey "(press any key)"
@@ -143,6 +155,7 @@
 int set_cursor(INT loc);
 int move_base(INT delta);
 int set_base(INT loc);
+int to_center();
 
 /*******************************************************************************/
 /* Curses functions declaration */
