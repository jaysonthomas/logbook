// Function to load the checkbox states from localStorage
function loadCheckboxState() {
  document.querySelectorAll('input[type="checkbox"]').forEach((checkbox) => {
    const id = checkbox.id;
    const savedState = localStorage.getItem(id); // Retrieve state from localStorage
    if (savedState === 'true') {
      checkbox.checked = true;
    } else if (savedState === 'false') {
      checkbox.checked = false;
    }
  });
}

// Function to save the checkbox state to localStorage
function saveCheckboxState() {
  document.querySelectorAll('input[type="checkbox"]').forEach((checkbox) => {
    const id = checkbox.id;
    localStorage.setItem(id, checkbox.checked); // Save state to localStorage
  });
}

// Load the state on page load
window.onload = loadCheckboxState;

// Save the state on checkbox change
document.querySelectorAll('input[type="checkbox"]').forEach((checkbox) => {
  checkbox.addEventListener('change', saveCheckboxState);
});

