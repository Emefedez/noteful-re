import {inkOpacity} from './timeline.js';
export function indexTimedInk(container, timings) {
 const byId = new Map(timings.map(timing => [timing.item_id, timing]));
 return [...container.querySelectorAll('[data-item]')].flatMap(el => {
  const timing = byId.get(el.dataset.item);
  return timing ? [{el, timing, opacity:null}] : [];
 });
}
export function updateTimedInk(items, recordingId, time) {
 for (const item of items) {
  const opacity = inkOpacity(item.timing.recording_id === recordingId ? item.timing : null, time);
  if (item.opacity !== opacity) { item.el.setAttribute('opacity', opacity); item.opacity = opacity; }
 }
}
