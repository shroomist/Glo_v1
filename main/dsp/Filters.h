/*
 * Filters.h
 *
 *  Created on: Apr 27, 2016
 *      Author: mario
 *
 *  This file is part of the Gecho Loopsynth & Glo Firmware Development Framework.
 *  It can be used within the terms of CC-BY-NC-SA license.
 *  It must not be distributed separately.
 *
 *  Find more information at:
 *  http://phonicbloom.com/diy/
 *  http://gechologic.com/gechologists/
 *
 */

#ifndef FILTERS_H_
#define FILTERS_H_

#include "IIR_filters.h"
#include <hw/codec.h>
#include <MusicBox.h>

#define FILTERS 22 //30 //20 //18 //16
#define ACCORD MINOR

#define CHORD_MAX_VOICES (FILTERS/2)	//two channels per voice
#define FILTERS_FREQ_CORRECTION 1.035
#define MELODY_MIXING_VOLUME 1.5f

//((FILTERS/2)-1) //last one, numbered from 0
//((FILTERS/2)-2) //one before last, numbered from 0

#if FILTERS==22
#define DEFAULT_MELODY_VOICE 10 //last one, numbered from 0
#define DEFAULT_ARPEGGIATOR_FILTER_PAIR 9 //one before last, numbered from 0
#endif

#if FILTERS==20
#define DEFAULT_MELODY_VOICE 9 //last one, numbered from 0
#define DEFAULT_ARPEGGIATOR_FILTER_PAIR 8 //one before last, numbered from 0
#endif

#if FILTERS==18
#define DEFAULT_MELODY_VOICE 8 //last one, numbered from 0
#define DEFAULT_ARPEGGIATOR_FILTER_PAIR 7 //one before last, numbered from 0
#endif

#define WIND_FILTERS 8
#define DEFAULT_WIND_VOICES (WIND_FILTERS/2)

#define FILTERS_RESONANCE_DEFAULT	0.99f
#define FILTERS_RESONANCE_HIGH		0.995f
#define FILTERS_RESONANCE_HIGHER	0.997f
#define FILTERS_RESONANCE_HIGHEST	0.999f
#define FILTERS_RESONANCE_STEP		0.005f

typedef struct {

	float volume_coef,volume_f,resonance;
	float mixing_volumes[FILTERS];

	int melody_filter_pair; //between 0 and CHORD_MAX_VOICES
	int arpeggiator_filter_pair; //between 0 and CHORD_MAX_VOICES

	float tuning_chords_l, tuning_chords_r, tuning_arp_l, tuning_arp_r, tuning_melody_l, tuning_melody_r;

} FILTERS_PARAMS;

class Filters
{
	public:

		IIR_Filter *iir2[FILTERS];// = NULL;
		//IIR_Filter *iir3[FILTERS];
		FILTERS_PARAMS fp;
		MusicBox *chord;

		Filters(int song_id, float default_resonance);
		~Filters(void);

		void setup();
		void setup(int filters_type_and_order);
		void release();

		void update_resonance();

		//void start_update_filters(int f1, int f2, int f3, int f4, float freq1, float freq2, float freq3, float freq4);
		void start_update_filters_pairs(int *filter_n, float *freq, int filters_to_update);
		void start_next_chord(int skip_voices);
		void start_next_melody_note();
		void progress_update_filters(Filters *fil, bool reset_buffers);
		void start_nth_chord(int chord_n);
		void set_melody_voice(int filter_pair, int melody_id);
		void add_to_update_filters_pairs(int filter_n, float freq, float tuning_l, float tuning_r);

	private:

		int update_filters_f[CHORD_MAX_VOICES*2 + 2]; //also two spaces for updating melody
		float update_filters_freq[CHORD_MAX_VOICES*2 + 2]; //also two spaces for updating melody
		int update_filters_loop;
};

#endif /* FILTERS_H_ */
