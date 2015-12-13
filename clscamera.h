#ifndef CLSCAMERA_H
#define CLSCAMERA_H
#include <QObject>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <getopt.h>             /* getopt_long() */

#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <jpeglib.h> // sudo apt-get install libjpeg-dev

#include <linux/videodev2.h>

#include <QTimer>

#define CLEAR(x) memset(&(x), 0, sizeof(x))

class clsCamera : public QObject
{
    Q_OBJECT
public:
    int mainCamera();
    clsCamera(QObject *parent = 0);
    ~clsCamera();
    enum io_method {
        IO_METHOD_READ,
        IO_METHOD_MMAP,
        IO_METHOD_USERPTR,
    };

    struct buffer {
        void   *start;
        size_t  length;
    };
//    const struct option
//            long_options[] = {
//    { "device", required_argument, NULL, 'd' },
//    { "help",   no_argument,       NULL, 'h' },
//    { "mmap",   no_argument,       NULL, 'm' },
//    { "read",   no_argument,       NULL, 'r' },
//    { "userp",  no_argument,       NULL, 'u' },
//    { "output", no_argument,       NULL, 'o' },
//    { "format", no_argument,       NULL, 'f' },
//    { "count",  required_argument, NULL, 'c' },
//    { 0, 0, 0, 0 }
//};

//    const char short_options[] = "d:hmruofc:";
private:
    char            *dev_name;
    enum io_method   io = IO_METHOD_MMAP;
    int              fd = -1;
    buffer          *buffers;
    unsigned int     n_buffers;
    int              out_buf;
    int              force_format;
    int              frame_count;

    QTimer timer;
    void errno_exit(const char *s);
    int xioctl(int fh, int request, void *arg);
    void process_image(const void *p, int size);
    int read_frame(void);
    void mainloop(void);
    void stop_capturing(void);
    void start_capturing(void);
    void uninit_device(void);
    void init_read(unsigned int buffer_size);
    void init_mmap(void);
    void init_userp(unsigned int buffer_size);
    void init_device(void);
    void close_device(void);
    void open_device(void);
    void usage(FILE *fp, int argc, char **argv);

    void closeDevise();

private slots:
     void timerTicked();
signals:
    void dataReady(const void *p, int size);

};

#endif // CLSCAMERA_H
