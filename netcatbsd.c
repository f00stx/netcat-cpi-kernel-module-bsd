#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/conf.h>
#include <sys/types.h>
#include <sys/uio.h>

#include "tracks/trk4.h"
#include "tracks/trk5.h"
#include "tracks/trk6.h"
#include "tracks/trk1.h"
#include "tracks/trk2.h"
#include "tracks/trk3.h"

static d_open_t netcat_open;
static d_close_t netcat_close;
static d_read_t netcat_read;
static d_write_t netcat_write;

static struct cdevsw netcat_cdevsw = {
	.d_version = D_VERSION,
	.d_open = netcat_open,
	.d_close = netcat_close,
	.d_read = netcat_read,
	.d_write = netcat_write,
	.d_name = "netcat",
};

static char *tracks[] = {netcat_cpi_trk1,
                         netcat_cpi_trk2,
                         netcat_cpi_trk3,
                         netcat_cpi_trk4,
                         netcat_cpi_trk5,
                         netcat_cpi_trk6};

static char *tracknames[] = {
	"Interrupt 0x7f",
	"The Internet is an Apt Motherfucker",
	"Interrupt 0x0d",
	"netcat",
	"Interrupt 0xbb",
	"Approximating the Circumference of the Earth"};

static unsigned long tracklens[] = {
	NETCAT_CPI_TRK1_LEN,
	NETCAT_CPI_TRK2_LEN,
	NETCAT_CPI_TRK3_LEN,
	NETCAT_CPI_TRK4_LEN,
	NETCAT_CPI_TRK5_LEN,
	NETCAT_CPI_TRK6_LEN};

static struct {
	char *msg;
	int current_track;
	size_t bytes;
	bool first_time;
} netcatdata;

static struct cdev *netcat_dev;

static int netcat_loader(struct module *module, int event, void *arg) {
	int e = 0;

	switch (event) {
		case MOD_LOAD:
			uprintf("netcat - Cycles Per Instruction - Kernel Module Edition - 2014 (FreeBSD flavoured)\n");
			uprintf("netcat is Brandon Lucia, Andrew Olmstead, and David Balatero\n");
			uprintf("On the web at http://netcat.co\n");
			uprintf("'ogg123 - < /dev/netcat' to play.\n");
			
			e = make_dev_p(MAKEDEV_CHECKNAME | MAKEDEV_WAITOK,
				&netcat_dev,
				&netcat_cdevsw,
				0,
				UID_ROOT,
				GID_WHEEL,
				0444,
				"netcat");
				
			if (e != 0) {
				break;
			}

			break;
		case MOD_UNLOAD:
			destroy_dev(netcat_dev);
			break;

		default:
			e = EOPNOTSUPP;
			break;
	}
	
	return (e);
}

static int netcat_open(struct cdev *dev __unused, int oflags __unused, int devtype __unused, struct thread *td __unused) {

	int error = 0;

	netcatdata.current_track = 0;
	netcatdata.bytes = 0;

	return (error);
}

static int netcat_close(struct cdev *dev __unused, int oflags __unused, int devtype __unused, struct thread *td __unused) {

	int error = 0;

	return (error);
}

static int netcat_read(struct cdev *dev __unused, struct uio *uio, int ioflag __unused) {

	int error = 0;
	
	if (netcatdata.first_time == true) {
		uprintf("Now playing track %d - %s\n",
		netcatdata.current_track + 1, tracknames[netcatdata.current_track]);
		netcatdata.first_time = false;
	}

	while (uio->uio_resid > 0) {
		int amt = MIN(uio->uio_resid, tracklens[netcatdata.current_track] - netcatdata.bytes);
		error = uiomove(tracks[netcatdata.current_track] + uio->uio_offset, amt, uio);
		netcatdata.bytes += amt;

		if (netcatdata.bytes == tracklens[netcatdata.current_track]) {
			uprintf("Now playing %s\n", tracknames[netcatdata.current_track]);
			netcatdata.bytes = 0;
			netcatdata.current_track = (netcatdata.current_track + 1) % 6;
		}
	}
	
	error = uiomove(tracks[netcatdata.current_track], 1, uio);

	if (error != 0) {
		uprintf("uiomove failed!\n");
	}

	return (error);
}

static int netcat_write(struct cdev *dev __unused, struct uio *uio, int ioflag __unused) {

	int error = EOPNOTSUPP;

	return (error);
}

DEV_MODULE(netcat, netcat_loader, NULL);
