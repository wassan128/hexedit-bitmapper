--- ../hexedit_orig/hexedit/interact.c	2008-11-08 00:50:57.000000000 +0900
+++ interact.c	2017-08-26 19:14:15.872012883 +0900
@@ -342,38 +342,38 @@
   switch (key) 
     {
     case KEY_RIGHT:
-    case CTRL('F'):
+    case 'l':
       forward_char();
       break;
 
     case KEY_LEFT:
-    case CTRL('B'):
+    case 'h':
       backward_char();
       break;
 
     case KEY_DOWN:
-    case CTRL('N'):
+    case 'j':
       next_line();
       break;
 
     case KEY_UP:
-    case CTRL('P'):
+    case 'k':
       previous_line();
       break;
 
-    case ALT('F'):
+    case 'L':
       forward_chars();
       break;
 
-    case ALT('B'):
+    case 'H':
       backward_chars();
       break;
 
-    case ALT('N'):
+    case 'J':
       next_lines();
       break;
 
-    case ALT('P'):
+    case 'K':
       previous_lines();
       break;
 
