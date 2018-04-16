/*
 * Copyright (C) 2018 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <sys/cdefs.h>
#include <sys/param.h>
#include <sys/types.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>

#include "dm.h"
#include "pci_core.h"
#include "virtio.h"
#include "mevent.h"
#include <linux/input.h>

static int virtio_input_debug;
#define DPRINTF(params) do { if (virtio_input_debug) printf params; } while (0)
#define WPRINTF(params) (printf params)

/*
 * Queue definitions.
 */
#define VIRTIO_INPUT_EVENT_QUEUE	0
#define VIRTIO_INPUT_STATUS_QUEUE	1
#define VIRTIO_INPUT_MAXQ		2

/*
 * Virtqueue size.
 */
#define VIRTIO_INPUT_RINGSZ		64

/*
 * Default size of the buffer used to hold events between SYN
 */
#define VIRTIO_INPUT_PACKET_SIZE	10

/*
 * Host capabilities
 */
#define VIRTIO_INPUT_S_HOSTCAPS		(VIRTIO_F_VERSION_1)

enum virtio_input_config_select {
	VIRTIO_INPUT_CFG_UNSET		= 0x00,
	VIRTIO_INPUT_CFG_ID_NAME	= 0x01,
	VIRTIO_INPUT_CFG_ID_SERIAL	= 0x02,
	VIRTIO_INPUT_CFG_ID_DEVIDS	= 0x03,
	VIRTIO_INPUT_CFG_PROP_BITS	= 0x10,
	VIRTIO_INPUT_CFG_EV_BITS	= 0x11,
	VIRTIO_INPUT_CFG_ABS_INFO	= 0x12,
};

struct virtio_input_absinfo {
	uint32_t min;
	uint32_t max;
	uint32_t fuzz;
	uint32_t flat;
	uint32_t res;
};

struct virtio_input_devids {
	uint16_t bustype;
	uint16_t vendor;
	uint16_t product;
	uint16_t version;
};

struct virtio_input_event {
	uint16_t type;
	uint16_t code;
	uint32_t value;
};

/*
 * Device-specific configuration registers
 * To query a specific piece of configuration information FE driver sets
 * "select" and "subsel" accordingly, information size is returned in "size"
 * and information data is returned in union "u"
 */
struct virtio_input_config {
	uint8_t    select;
	uint8_t    subsel;
	uint8_t    size;
	uint8_t    reserved[5];
	union {
		char string[128];
		uint8_t bitmap[128];
		struct virtio_input_absinfo abs;
		struct virtio_input_devids ids;
	} u;
};

struct virtio_input_event_elem {
	struct virtio_input_event		event;
	struct iovec				iov;
	uint16_t				idx;
};

/*
 * Per-device struct
 */
struct virtio_input {
	struct virtio_base			base;
	struct virtio_vq_info			queues[VIRTIO_INPUT_MAXQ];
	pthread_mutex_t				mtx;
	struct mevent				*mevp;
	uint64_t				features;
	struct virtio_input_config		cfg;
	char					*evdev;
	char					*serial;
	int					fd;
	bool					ready;

	struct virtio_input_event_elem		*event_queue;
	uint32_t				event_qsize;
	uint32_t				event_qindex;
};

static void virtio_input_reset(void *);
static void virtio_input_neg_features(void *, uint64_t);
static void virtio_input_set_status(void *, uint64_t);
static int virtio_input_cfgread(void *, int, int, uint32_t *);
static int virtio_input_cfgwrite(void *, int, int, uint32_t);

static struct virtio_ops virtio_input_ops = {
	"virtio_input",			/* our name */
	VIRTIO_INPUT_MAXQ,		/* we support VTCON_MAXQ virtqueues */
	sizeof(struct virtio_input_config),	/* config reg size */
	virtio_input_reset,		/* reset */
	NULL,				/* device-wide qnotify */
	virtio_input_cfgread,		/* read virtio config */
	virtio_input_cfgwrite,		/* write virtio config */
	virtio_input_neg_features,	/* apply negotiated features */
	virtio_input_set_status,	/* called on guest set status */
	VIRTIO_INPUT_S_HOSTCAPS,	/* our capabilities */
};

static void
virtio_input_reset(void *vdev)
{
	/* to be implemented */
}

static void
virtio_input_neg_features(void *vdev, uint64_t negotiated_features)
{
	/* to be implemented */
}

static void
virtio_input_set_status(void *vdev, uint64_t status)
{
	/* to be implemented */
}

static int
virtio_input_cfgread(void *vdev, int offset, int size, uint32_t *retval)
{
	/* to be implemented */
	return 0;
}

static int
virtio_input_cfgwrite(void *vdev, int offset, int size, uint32_t val)
{
	/* to be implemented */
	return 0;
}

static void
virtio_input_notify_event_vq(void *vdev, struct virtio_vq_info *vq)
{
	DPRINTF(("%s\n", __func__));
}

static void
virtio_input_notify_status_vq(void *vdev, struct virtio_vq_info *vq)
{
	/* to be implemented */
}

static void
virtio_input_read_event(int fd __attribute__((unused)),
			enum ev_type t __attribute__((unused)),
			void *arg)
{
	/* to be implemented */
}

static int
virtio_input_init(struct vmctx *ctx, struct pci_vdev *dev, char *opts)
{
	struct virtio_input *vi;
	pthread_mutexattr_t attr;
	bool mutex_initialized = false;
	char *opt;
	int flags, ver;
	int rc;

	/* get evdev path from opts
	 * -s n,virtio-input,/dev/input/eventX[,serial]
	 */
	if (!opts) {
		WPRINTF(("%s: evdev path is NULL\n", __func__));
		return -1;
	}

	vi = calloc(1, sizeof(struct virtio_input));
	if (!vi) {
		WPRINTF(("%s: out of memory\n", __func__));
		return -1;
	}

	opt = strsep(&opts, ",");
	if (!opt) {
		WPRINTF(("%s: evdev path is NULL\n", __func__));
		goto fail;
	}

	vi->evdev = strdup(opt);
	if (!vi->evdev) {
		WPRINTF(("%s: strdup failed\n", __func__));
		goto fail;
	}

	if (opts) {
		vi->serial = strdup(opts);
		if (!vi->serial) {
			WPRINTF(("%s: strdup serial failed\n", __func__));
			goto fail;
		}
	}

	vi->fd = open(vi->evdev, O_RDWR);
	if (vi->fd < 0) {
		WPRINTF(("open %s failed %d\n", vi->evdev, errno));
		goto fail;
	}
	flags = fcntl(vi->fd, F_GETFL);
	fcntl(vi->fd, F_SETFL, flags | O_NONBLOCK);

	rc = ioctl(vi->fd, EVIOCGVERSION, &ver); /* is it a evdev device? */
	if (rc < 0) {
		WPRINTF(("%s: get version failed\n", vi->evdev));
		goto fail;
	}

	rc = ioctl(vi->fd, EVIOCGRAB, 1); /* exclusive access */
	if (rc < 0) {
		WPRINTF(("%s: grab device failed %d\n", vi->evdev, errno));
		goto fail;
	}

	/* init mutex attribute properly to avoid deadlock */
	rc = pthread_mutexattr_init(&attr);
	if (rc)
		DPRINTF(("mutexattr init failed with erro %d!\n", rc));
	rc = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	if (rc)
		DPRINTF(("vtinput: mutexattr_settype failed with "
			"error %d!\n", rc));
	rc = pthread_mutex_init(&vi->mtx, &attr);
	if (rc)
		DPRINTF(("vtinput: pthread_mutex_init failed with "
			"error %d!\n", rc));
	mutex_initialized = (rc == 0) ? true : false;

	vi->event_qsize = VIRTIO_INPUT_PACKET_SIZE;
	vi->event_qindex = 0;
	vi->event_queue = calloc(vi->event_qsize,
		sizeof(struct virtio_input_event_elem));
	if (!vi->event_queue) {
		WPRINTF(("vtinput: could not alloc event queue buf\n"));
		goto fail;
	}

	vi->mevp = mevent_add(vi->fd, EVF_READ, virtio_input_read_event, vi);
	if (vi->mevp == NULL) {
		WPRINTF(("vtinput: could not register event\n"));
		goto fail;
	}

	virtio_linkup(&vi->base, &virtio_input_ops, vi, dev, vi->queues);
	vi->base.mtx = &vi->mtx;

	vi->queues[VIRTIO_INPUT_EVENT_QUEUE].qsize = VIRTIO_INPUT_RINGSZ;
	vi->queues[VIRTIO_INPUT_EVENT_QUEUE].notify =
		virtio_input_notify_event_vq;

	vi->queues[VIRTIO_INPUT_STATUS_QUEUE].qsize = VIRTIO_INPUT_RINGSZ;
	vi->queues[VIRTIO_INPUT_STATUS_QUEUE].notify =
		virtio_input_notify_status_vq;

	/* initialize config space */
	pci_set_cfgdata16(dev, PCIR_DEVICE, 0x1040 + VIRTIO_TYPE_INPUT);
	pci_set_cfgdata16(dev, PCIR_VENDOR, VIRTIO_VENDOR);
	pci_set_cfgdata8(dev, PCIR_CLASS, PCIC_INPUTDEV);
	pci_set_cfgdata8(dev, PCIR_SUBCLASS, PCIS_INPUTDEV_OTHER);
	pci_set_cfgdata16(dev, PCIR_SUBDEV_0, 0x1040 + VIRTIO_TYPE_INPUT);
	pci_set_cfgdata16(dev, PCIR_SUBVEND_0, VIRTIO_VENDOR);

	if (virtio_interrupt_init(&vi->base, virtio_uses_msix())) {
		DPRINTF(("%s, interrupt_init failed!\n", __func__));
		goto fail;
	}
	rc = virtio_set_modern_bar(&vi->base, true);

	return rc;

fail:
	if (vi) {
		if (mutex_initialized)
			pthread_mutex_destroy(&vi->mtx);
		if (vi->event_queue) {
			free(vi->event_queue);
			vi->event_queue = NULL;
		}
		if (vi->mevp) {
			mevent_delete(vi->mevp);
			vi->mevp = NULL;
		}
		if (vi->fd > 0) {
			close(vi->fd);
			vi->fd = -1;
		}
		if (vi->serial) {
			free(vi->serial);
			vi->serial = NULL;
		}
		if (vi->evdev) {
			free(vi->evdev);
			vi->evdev = NULL;
		}
		free(vi);
		vi = NULL;
	}
	return -1;
}

static void
virtio_input_deinit(struct vmctx *ctx, struct pci_vdev *dev, char *opts)
{
	/* to be implemented */
}

struct pci_vdev_ops pci_ops_virtio_input = {
	.class_name	= "virtio-input",
	.vdev_init	= virtio_input_init,
	.vdev_deinit	= virtio_input_deinit,
	.vdev_barwrite	= virtio_pci_write,
	.vdev_barread	= virtio_pci_read
};
DEFINE_PCI_DEVTYPE(pci_ops_virtio_input);