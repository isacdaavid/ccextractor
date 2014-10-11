#ifndef __Timing_H__

#include "ccx_common_platform.h"

struct gop_time_code
{
	int drop_frame_flag;
	int time_code_hours;
	int time_code_minutes;
	int marker_bit;
	int time_code_seconds;
	int time_code_pictures;
	int inited;
	LLONG ms;
};

struct ccx_common_timing_settings_t {
	int disable_sync_check; // If 1, timeline jumps will be ignored. This is important in several input formats that are assumed to have correct timing, no matter what.
	int no_sync; // If 1, there will be no sync at all. Mostly useful for debugging.
	int is_elementary_stream; // Needs to be set, as it's used in set_fts.
	LLONG *file_position; // The position of the file
};
extern struct ccx_common_timing_settings_t ccx_common_timing_settings;

struct ccx_boundary_time
{
	int hh,mm,ss;
	LLONG time_in_ms;
	int set;
};

// Count 608 (per field) and 708 blocks since last set_fts() call
extern int cb_field1, cb_field2, cb_708;

extern int pts_set; //0 = No, 1 = received, 2 = min_pts set
extern int MPEG_CLOCK_FREQ; // This is part of the standard

extern LLONG min_pts, max_pts, sync_pts, current_pts;
extern int max_dif;
extern unsigned pts_big_change;

extern LLONG fts_now; // Time stamp of current file (w/ fts_offset, w/o fts_global)
extern LLONG fts_offset; // Time before first sync_pts
extern LLONG fts_fc_offset; // Time before first GOP
extern LLONG fts_max; // Remember the maximum fts that we saw in current file
extern LLONG fts_global; // Duration of previous files (-ve mode)

extern enum ccx_frame_type current_picture_coding_type;
extern int current_tref; // Store temporal reference of current frame
extern double current_fps;
extern int frames_since_ref_time;
extern unsigned total_frames_count;

extern int current_field;

extern struct gop_time_code gop_time, first_gop_time, printed_gop;
extern LLONG fts_at_gop_start;
extern int gop_rollover;

void ccx_common_timing_init(LLONG *file_position, int no_sync);

void set_fts(void);
LLONG get_fts(void);
LLONG get_fts_max(void);
char *print_mstime(LLONG mstime);
char *print_mstime2buf(LLONG mstime, char *buf);
void print_debug_timing(void);
int gop_accepted(struct gop_time_code* g);
void calculate_ms_gop_time(struct gop_time_code *g);

#define __Timing_H__
#endif