function initializePage(chapterTitle, rootPath = "../../../../") {
    // 1. Update Document Title
    document.title = chapterTitle;

    // 2. Helper to inject scripts so they actually EXECUTE
    const injectScript = (src, isAsync = false) => {
        const script = document.createElement('script');
        script.src = src;
        script.async = isAsync;
        // Keep the MathJax ID if needed
        if (src.includes('tex-chtml.js')) script.id = 'MathJax-script';
        document.head.appendChild(script);
    };

    // 3. Helper to inject CSS
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

    // MathJax Config MUST load before MathJax itself
    injectScript(`${rootPath}logbook-mathjax-config.js`);
    injectScript("https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-chtml.js");
    injectScript("https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.6.0/highlight.min.js");
    injectScript(`${rootPath}logbook.js`);

    // 4. Inject the Header (HTML injection works fine for non-script tags)
    const d = new Date(document.lastModified);
    const dateStr = `${d.getFullYear()}-${d.getMonth() + 1}-${d.getDate()}`;

    const bodyHeader = `
        <div data-type="titlepage" pdf="no">
            <header>
                <h1><a href="${rootPath}index.html" style="text-decoration:none;">Logbook</a></h1>
                <p style="font-size: 18px;"><a href="${rootPath}pages/bio/main.html">Jayson Wynne-Thomas</a></p>
                <p style="font-size: 14px; text-align: right;"> 
                    Last modified <span>${dateStr}</span>
                </p>
            </header>
        </div>
    `;

    // Ensure body exists before injecting
    if (document.body) {
        document.body.insertAdjacentHTML('afterbegin', bodyHeader);
    } else {
        window.addEventListener('DOMContentLoaded', () => {
            document.body.insertAdjacentHTML('afterbegin', bodyHeader);
        });
    }
}