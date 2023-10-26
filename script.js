function updateConsumptionValue() {
    // Simulate real-time data updates (replace with actual data from IoT sensors)
    const consumptionData = Math.floor(Math.random() * 100) + 50; // Simulated consumption value
    const consumptionValue = document.getElementById('consumption-value');

    consumptionValue.innerText = consumptionData + ' liters';
}

// Simulate real-time data updates every 5 seconds
setInterval(updateConsumptionValue, 5000);
updateConsumptionValue(); // Initial update
