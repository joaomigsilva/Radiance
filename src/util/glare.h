/* Copyright (c) 1991 Regents of the University of California */

/* SCCSid "$SunId$ LBL" */

/*
 * Common data structures for glare source finding routines
 */

#include "standard.h"
#include "view.h"
#include "color.h"
#include "setscan.h"

#define GLAREBR		10.0		/* glare source is this * avg. lum. */

#define SAMPDENS	50		/* samples per unit in image */
#define TSAMPSTEP	10		/* sample step to compute threshold */

#define SEPS		2		/* sources this close ==> contig. */

extern VIEW	ourview;		/* our view */
extern VIEW	pictview;		/* picture view */
extern VIEW	leftview, rightview;	/* leftmost and rightmost views */

extern int	verbose;		/* verbose reporting */
extern char	*progname;		/* global argv[0] */

extern ANGLE	glarang[];		/* glare calculation angles */
extern int	nglarangs;
extern int	hsize;			/* horizontal size */
extern int	hlim;			/* horizontal limit of central view */

#define nglardirs	(2*nglarangs+1)
#define maxtheta	((PI/180.)*glarang[nglarangs-1])
#define vsize		SAMPDENS
#define h_theta(h)	((double)(h)/(double)SAMPDENS)

extern struct illum {
	float	theta;		/* glare direction */
	float	lcos, lsin;	/* cosine and sine to left view */
	float	rcos, rsin;	/* cosine and sine to right view */
	double	sum;		/* sum of indirect luminances */
	int	n;		/* number of values in sum */
} *indirect;		/* array of indirect illuminances */

struct srcspan {
	short	v;		/* vertical position */
	short	l, r;		/* left and right horizontal limits */
	float	brsum;		/* sum of brightnesses for this span */
	struct srcspan	*next;	/* next source span in list */
};

extern struct source {
	FVECT	dir;		/* source direction */
	float	dom;		/* solid angle of source */
	float	brt;		/* average source brightness */
	struct srcspan	*first;	/* first span for this source */
	struct source	*next;	/* next source in list */
} *donelist;			/* finished sources */

extern double	getviewpix();
