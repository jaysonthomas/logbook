function initializePage(chapterTitle, rootPath = "../../../../") {
    document.title = chapterTitle;

    const injectScript = (src, isAsync = false, callback = null) => {
        const script = document.createElement('script');
        script.src = src;
        script.async = isAsync;
        if (src.includes('tex-chtml.js')) script.id = 'MathJax-script';
        
        // This callback runs once the script is actually downloaded and ready
        if (callback) {
            script.onload = callback;
        }
        
        document.head.appendChild(script);
    };

    const injectCSS = (href) => {
        const link = document.createElement('link');
        link.rel = 'stylesheet';
        link.type = 'text/css';
        link.href = href;
        document.head.appendChild(link);
    };

    // --- Execute Injections ---
    injectCSS("https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.6.0/styles/atom-one-light.min.css");
    injectCSS(`${rootPath}logbook.css`);

    injectScript(`${rootPath}logbook-mathjax-config.js`);
    injectScript("https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-chtml.js");
    injectScript(`${rootPath}logbook.js`);

    // FIX FOR HIGHLIGHT.JS:
    // We pass a callback to run highlightAll() only AFTER the file has loaded
    injectScript("https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.6.0/highlight.min.js", true, () => {
        hljs.highlightAll();
    });

    // --- Inject the Header ---
    const d = new Date(document.lastModified);
    const dateStr = `${d.getFullYear()}-${d.getMonth() + 1}-${d.getDate()}`;
    const bodyHeader = `
        <div data-type="titlepage" pdf="no">
            <header>
                <h1><a href="${rootPath}index.html" style="text-decoration:none;">Logbook</a></h1>
                <p style="font-size: 18px;"><a href="${rootPath}pages/bio/main.html">Jayson Wynne-Thomas</a></p>
                <p style="font-size: 14px; text-align: right;">Last modified <span>${dateStr}</span></p>
            </header>
        </div>`;

    if (document.body) {
        document.body.insertAdjacentHTML('afterbegin', bodyHeader);
    } else {
        window.addEventListener('DOMContentLoaded', () => {
            document.body.insertAdjacentHTML('afterbegin', bodyHeader);
        });
    }
}