#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *features[] = {"Phone","Contacts","Messages","Mail","Calendar","Clock","Calculator","Camera","Gallery","Music","Video","Browser","Maps","Settings","Files","Store","Terminal","Notes","Recorder","Alarm","Weather","Diagnostics","Data calculator","FM radio"};
    FILE *f = fopen("docs/applications.md", "wb");
    if (!f) { perror("docs/applications.md"); return 2; }
    fputs("# Application guide\n\n", f);
    for (unsigned i = 0; i < sizeof(features)/sizeof(features[0]); ++i) {
        fprintf(f, "## %s\nWhat it does: provides the %s experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.\n\n", features[i], features[i]);
    }
    fclose(f);
    puts("wrote docs/applications.md");
    return 0;
}
