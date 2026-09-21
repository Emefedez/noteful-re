// Keep model timestamps on the recording's clock; never invent word timings.
export function timedWords(chunks, duration) {
  return (chunks || []).flatMap(({ text, timestamp }) => {
    const [start, end] = timestamp || [];
    if (!text?.trim() || !Number.isFinite(start) || start < 0 || start >= duration)
      return [];
    return [{ text: text.trim(), start, end: Math.min(duration,
      Number.isFinite(end) && end > start ? end : duration) }];
  }).sort((a, b) => a.start - b.start).map((word, i, words) => ({
    ...word, end: Math.min(word.end, words[i + 1]?.start ?? duration),
  }));
}

export function wordAt(words, time) {
  let low = 0, high = words.length;
  while (low < high) {
    const mid = (low + high) >>> 1;
    if (words[mid].start <= time) low = mid + 1;
    else high = mid;
  }
  const index = low - 1;
  return index >= 0 && time < words[index].end ? index : -1;
}
