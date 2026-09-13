// Whole-stroke pen-down timing. Preserve original ink/highlighter opacity inside.
export function inkOpacity(timing,time){return timing && time<timing.start?0.2:1;}
