[1,3,6,2,5,1].each do |d|
  (range -3, 3).each do |i|
    play_chord (chord_degree d, :c, :major, 3, invert: i)
    sleep 0.5
  end
end
play_pattern_timed [74,67,66,67],[0.5,0.25,0.25,0.5] #b25
play_pattern_timed [76,67,66,67],[0.5,0.25,0.25,0.5] #b26
play_pattern_timed [74,72,71],[0.5] #b27
play_pattern_timed [69,67,66,67,69],[0.5,0.25,0.25,0.25,0.5] #b28
play_pattern_timed [62,64,66,67,69,71],[0.25] #b29
play_pattern_timed [72,71,69],[0.5] #b30
play_pattern_timed [71,74,67,66],[0.25,0.25,0.5,0.5] #b31
play_chord [55,59]#b9=b1
sleep 1
play 40
sleep 0.2
play_pattern_timed [55,59,55],[0.5] #b10
play_pattern_timed [60],[1.5] #b11=b3
play_pattern_timed [59,60,59,57,5],[0.5,0.2,0.2,0.25,0.25] #b12=b4]
play_pattern_timed [55,59],[1,0.5] #b14
play_pattern_timed [55,43],[1,0.5] #b16
use_sample_bpm :loop_compus, num_beats: 3
live_loop :loopr do
  play_chord [67,59] #b32
  sleep 1
  sample :loop_compus, rate: [0.5, 1, 1, 1, 1, 2].choose unless one_in(10)
  sleep 3
end
live_loop :ind do
  sample :loop_industrial, beat_stretch: 1
  sleep 2
end
play_pattern_timed [74],[0.5]#b9 = b1
play_pattern_timed [72,74,76,78],[0.25]
play_pattern_timed [67,69,71,72],[0.25]
play_pattern_timed [74,67,67],[0.5]#b10=b2
play_pattern_timed [76],[0.5]#b11=b3
play_pattern_timed [72,74,76,78],[0.5]
play_pattern_timed [79,67,67],[0.5]#b12=b4
play_pattern_timed [72],[0.5] #b13=b5
play_pattern_timed [74,72,71,69],[0.5]
play_pattern_timed [67],[1.5] #b16
play_pattern_timed [74,72,71],[0.7] #b27
live_loop :bass do
  sample :bass_voxy_c, amp: rrand(0.1, 0.3), rate: [0.6, 0.4, 1, 2,2,4].choose if one_in(4)
  use_synth :mod_pulse
  use_synth_defaults mod_invert_wave: 1
  play :C3, mod_range: 20, amp: rrand(0.5, 1), mod_phase: [0.5, 0.5, 1].choose, release: 1, cutoff: rrand(60, 90)
  play :C2, mod_range: [30, 36, 34].choose, amp: 1, mod_phase: 0.25, cutoff: 60
  sleep 2
end
