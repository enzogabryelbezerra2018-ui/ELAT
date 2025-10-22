#ifndef RESET_TRANSITION_H
#define RESET_TRANSITION_H

namespace ResetTransition {

    void fade_in_text(const char* str,int y,int duration_ms);
    void fade_out_text(const char* str,int y,int duration_ms);
    void animate_dots(int y,int duration_sec);
    void transition_boot_to_reset();

} // namespace ResetTransition

#endif
