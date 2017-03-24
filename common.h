/* Time-stamp: <02 fév 2013 11:27 queinnec@enseeiht.fr> */

/* Formatted write on a file descriptor. Works like printf. */
void writef(int fd, const char *fmt, ...)
    __attribute__ ((format (printf, 2, 3)));

/* Read a complete http request from the file descriptor fd and return the first line.
 * A line is a sequence of characters ending with \n or \r\n; the trailing \n or \r\n is dropped.
 * The request ends with \r\n\r\n.
 * The line returned is allocated with malloc; the caller must free it when finished.
 * read_request has an arbitrary internal limit on the line length: a longer line will be truncated (beurk).
 */
char *read_request(int fd);

/* Known methods. */
#define REQUEST_GET 1
#define REQUEST_UNKNOWN 10

/* Parse the request, returns method and url.
 * The parsing is not solid at all !
 * line is modified in place, and filename points into it. */
void parse_request(char *line, int *method, char **filename);

/* Return the mimetype for the given filename. */
char *find_mimetype(char *filename);
