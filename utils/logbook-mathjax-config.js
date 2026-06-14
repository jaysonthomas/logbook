window.MathJax = {
  startup: {
    // Ensures that MathJax doesn't automatically typeset the document when it loads. Typesetting needs to be manually triggered later using a js script.
    typeset: false
  },
  tex: {
    // Delimiters for inline and display math.
    inlineMath: [ ['$','$'], ["\\(","\\)"] ],
    displayMath: [ ['$$','$$'], ["\\[","\\]"] ],

    // Allows the use of backslash escapes in the text.
    processEscapes: true,

    // Enables automatic equation numbering in the AMS style.
    tags: 'ams',

    // Includes the cancel and color packages.
    packages: {'[+]': ['cancel', 'color']}
  },
  svg: {
    // Ensures that the font cache is shared across the document.
    fontCache: 'global'
  },
  // Ensures that the required packages are loaded.
  loader: {load: ['[tex]/cancel', '[tex]/color']},
};
