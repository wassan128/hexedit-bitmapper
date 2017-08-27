--- display.c.orig	2013-03-02 06:58:56.000000000 +0900
+++ display.c	2015-06-17 20:35:41.000000000 +0900
@@ -79,6 +79,29 @@
   return TRUE;
 }
 
+int to_center()
+{
+  int delta, savecursor = cursor;
+  int center_line = (page / lineLength) / 2;
+  int cursor_line = cursor / lineLength;
+
+  if (mode == bySector)
+    return TRUE;
+
+  delta = (cursor_line - center_line) * lineLength;
+
+  if (base + delta < 0)
+    delta = -(base / lineLength) * lineLength;
+
+  while (tryloc(base + delta + page - lineLength) == FALSE)
+    delta -= lineLength;
+
+  move_base(delta);
+  move_cursor(-delta + (savecursor - cursor));
+
+  return TRUE;
+}
+
 
 int computeLineSize(void) { return computeCursorXPos(lineLength - 1, 0) + 1; }
 int computeCursorXCurrentPos(void) { return computeCursorXPos(cursor, hexOrAscii); }
@@ -108,9 +131,10 @@
   if (colored) {
     start_color();
     use_default_colors();
-    init_pair(1, COLOR_RED, -1);   /* null zeros */
-    init_pair(2, COLOR_GREEN, -1); /* control chars */
-    init_pair(3, COLOR_BLUE, -1);  /* extended chars */
+    init_pair(1, color_null_fg,     color_null_bg);     /* null zeros */
+    init_pair(2, color_control_fg,  color_control_bg);  /* control chars */
+    init_pair(3, color_extended_fg, color_extended_bg); /* extended chars */
+    init_pair(4, color_normal_fg,   color_normal_bg);   /* printable chars */
   }
 #endif
 
@@ -175,6 +199,12 @@
   printw("-%c%c  %s       --0x%llX", i, i, baseName, base + cursor);
   if (MAX(fileSize, lastEditedLoc)) printw("/0x%llX", getfilesize());
   if (mode == bySector) printw("--sector %lld", (base + cursor) / SECTOR_SIZE);
+  {
+    int c = (cursor < nbBytes) ? buffer[cursor] : ' ';
+    printw("--%3d--", c);
+    for (i = 0; i < 8; i++)
+      printw("%c", (c & (1 << (7 - i))) ? '1' : '0');
+  }
 
   move(cursor / lineLength, computeCursorXCurrentPos());
 }
@@ -182,28 +212,45 @@
 void displayLine(int offset, int max)
 {
   int i;
+  int vc, cursor_line, cursor_clmn, attr, cursor_attr;
 
-  PRINTW(("%08lX   ", (int) (base + offset)));
+  cursor_line = (cursor >= offset && cursor < offset + lineLength);
+  PRINTW(("%08lX%c", (int) (base + offset), (cursor_line ? '>' : ' ')));
+  if (cursor < max) {
+    cursor_attr = bufferAttr[cursor];
+    bufferAttr[cursor] = cursor_attr | A_UNDERLINE;
+  }
   for (i = offset; i < offset + lineLength; i++) {
-    if (i > offset) MAXATTRPRINTW(bufferAttr[i] & MARKED, (((i - offset) % blocSize) ? " " : "  "));
+    cursor_clmn = ((i % lineLength) == (cursor % lineLength));
+    attr = (cursor_line && hexOrAscii) ? A_UNDERLINE : 0;
+    vc = (cursor_clmn && (hexOrAscii || (!hexOrAscii && cursor_line))) ? '|' : ' ';
+    MAXATTRPRINTW((bufferAttr[i] & MARKED) | attr, (((i - offset) % blocSize) ? "%c" : " %c", vc));
     if (i < max) {
       ATTRPRINTW(
 #ifdef HAVE_COLORS
 		 (!colored ? 0 :
 		  buffer[i] == 0 ? COLOR_PAIR(1) :
 		  buffer[i] < ' ' ? COLOR_PAIR(2) : 
-		  buffer[i] >= 127 ? COLOR_PAIR(3) : 0) |
+		  buffer[i] >= 127 ? COLOR_PAIR(3) : COLOR_PAIR(4)) |
+		 (bold ? A_BOLD : 0) |
 #endif
+		 attr |
 		 bufferAttr[i], ("%02X", buffer[i]));
     }
     else PRINTW(("  "));
   }
   PRINTW(("  "));
   for (i = offset; i < offset + lineLength; i++) {
+    cursor_clmn = ((i % lineLength) == (cursor % lineLength));
+    attr = (!hexOrAscii && (cursor_clmn || cursor_line)) ? A_REVERSE : 0;
     if (i >= max) PRINTW((" "));
-    else if (buffer[i] >= ' ' && buffer[i] < 127) ATTRPRINTW(bufferAttr[i], ("%c", buffer[i]));
-    else ATTRPRINTW(bufferAttr[i], ("."));
+    else if (buffer[i] >= ' ' && buffer[i] < 127) ATTRPRINTW(bufferAttr[i] | attr, ("%c", buffer[i]));
+    else ATTRPRINTW(bufferAttr[i] | attr, ("."));
+  }
+  if (cursor < max) {
+    bufferAttr[cursor] = cursor_attr;
   }
+  PRINTW((""));
 }
 
 void clr_line(int line) { move(line, 0); clrtoeol(); }
