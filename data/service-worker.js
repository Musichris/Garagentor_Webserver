self.addEventListener('install', e => {
    e.waitUntil(
        caches.open('garagentor-cache').then(cache => {
            return cache.addAll([
                './Garagentor.html',
                './manifest.json',
                './icons/android-chrome-192x192.png',
                './icons/android-chrome-512x512.png'
            ]);
        })
    );
});

self.addEventListener('fetch', e => {
    e.respondWith(
        caches.match(e.request).then(response => response || fetch(e.request))
    );
});
