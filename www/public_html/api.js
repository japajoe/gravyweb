// This function will be executed when the document is fully loaded
document.addEventListener('DOMContentLoaded', function () {
    const button = document.getElementById('buttonSend');

    if (button) {
        // Register a click event
        button.addEventListener('click', function () {
            onButtonClick();
        });
    } 
});

// Define the URL to which you want to send the POST request
const url = 'api/v1';

// Data to be sent in the POST request
const data = {
    key1: 'value1',
    key2: 'value2'
};

function onButtonClick() {
    const responseArea = document.getElementById('responseArea');

    fetch(url, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
            // Add any other headers if needed
        },
        body: JSON.stringify(data), // Convert data to JSON format
    })
    .then(response => response.json()) // Parse the JSON response
    .then(data => {
        if (responseArea) {
            responseArea.innerText = JSON.stringify(data);
        } else {
            console.log('POST request successful:', data);            
        }
    })
    .catch(error => {
        if (responseArea) {
            responseArea.innerText = error;
        } else {
            console.error('Error during POST request:', error);
        }
    });
}