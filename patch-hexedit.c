--- hexedit.c.orig	2010-02-04 23:58:23.000000000 +0900
+++ hexedit.c	2015-06-17 20:35:48.000000000 +0900
@@ -43,10 +43,59 @@
 
 char * usage = "usage: %s [-s | --sector] [-m | --maximize]"
 #ifdef HAVE_COLORS 
-     " [--color]"
+     "\n"
+     " [--color]\n"
+     " [--color-null-fg {<color> | auto}]\n"
+     " [--color-null-bg {<color> | auto}]\n"
+     " [--color-control-fg {<color> | auto}]\n"
+     " [--color-control-bg {<color> | auto}]\n"
+     " [--color-normal-fg {<color> | auto}]\n"
+     " [--color-normal-bg {<color> | auto}]\n"
+     " [--color-extended-fg {<color> | auto}]\n"
+     " [--color-extended-bg {<color> | auto}]\n"
+     " [--bold]\n"
 #endif 
      " [-h | --help] filename\n";
 
+#ifdef HAVE_COLORS 
+int color_null_fg     = -1;
+int color_control_fg  = -1;
+int color_extended_fg = -1;
+int color_normal_fg   = COLOR_BLACK;
+int color_null_bg     = COLOR_RED;
+int color_control_bg  = COLOR_GREEN;
+int color_extended_bg = COLOR_BLUE;
+int color_normal_bg   = COLOR_WHITE;
+int bold = FALSE;
+
+int color_name_to_number(char *name)
+{
+  int i;
+  static struct {
+    char *name;
+    int number;
+  } name_to_number[] = {
+    { "black",   COLOR_BLACK },
+    { "red",     COLOR_RED },
+    { "green",   COLOR_GREEN },
+    { "yellow",  COLOR_YELLOW },
+    { "blue",    COLOR_BLUE },
+    { "magenta", COLOR_MAGENTA },
+    { "cyan",    COLOR_CYAN },
+    { "white",   COLOR_WHITE },
+    { "auto",    -1 },
+    { NULL, -1 }
+  };
+
+  for (i = 0; name_to_number[i].name; i++) {
+    if (!strcmp(name, name_to_number[i].name))
+      return name_to_number[i].number;
+  }
+
+  return -1;
+}
+#endif
+
 
 /*******************************************************************************/
 /* main */
@@ -65,6 +114,40 @@
 #ifdef HAVE_COLORS
       else if (streq(*argv, "--color"))
 	colored = TRUE;
+      else if (streq(*argv, "--color-null-fg") && (argc > 1)) {
+	argv++; argc--;
+	color_null_fg = color_name_to_number(*argv);
+      }
+      else if (streq(*argv, "--color-null-bg") && (argc > 1)) {
+	argv++; argc--;
+	color_null_bg = color_name_to_number(*argv);
+      }
+      else if (streq(*argv, "--color-control-fg") && (argc > 1)) {
+	argv++; argc--;
+	color_control_fg = color_name_to_number(*argv);
+      }
+      else if (streq(*argv, "--color-control-bg") && (argc > 1)) {
+	argv++; argc--;
+	color_control_bg = color_name_to_number(*argv);
+      }
+      else if (streq(*argv, "--color-extended-fg") && (argc > 1)) {
+	argv++; argc--;
+	color_extended_fg = color_name_to_number(*argv);
+      }
+      else if (streq(*argv, "--color-extended-bg") && (argc > 1)) {
+	argv++; argc--;
+	color_extended_bg = color_name_to_number(*argv);
+      }
+      else if (streq(*argv, "--color-normal-fg") && (argc > 1)) {
+	argv++; argc--;
+	color_normal_fg = color_name_to_number(*argv);
+      }
+      else if (streq(*argv, "--color-normal-bg") && (argc > 1)) {
+	argv++; argc--;
+	color_normal_bg = color_name_to_number(*argv);
+      }
+      else if (streq(*argv, "--bold"))
+	bold = TRUE;
 #endif
       else if (streq(*argv, "--")) {
 	argv++; argc--;
