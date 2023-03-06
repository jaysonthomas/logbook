window.MathJax = {
  startup: {
    typeset: false
  },
  tex: {
    inlineMath: [ ['$','$'], ["\\(","\\)"] ],
    displayMath: [ ['$$','$$'], ["\\[","\\]"] ],
    processEscapes: true,
    tags: 'ams',
    packages: {'[+]': ['cancel']}
  },
  svg: {
    fontCache: 'global'
  },
  loader: {load: ['[tex]/cancel']},
};
