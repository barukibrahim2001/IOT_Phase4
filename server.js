const express = require('express');
const sqlite3 = require('sqlite3');
const { open } = require('sqlite');

const app = express();
const port = 3000;

// Open an SQLite database
const dbPromise = open({
    filename: './data.db',
    driver: sqlite3.Database
});

// Middleware to parse JSON data
app.use(express.json());

// API Routes

// Get a list of items
app.get('/items', async (req, res) => {
    const db = await dbPromise;
    const items = await db.all('SELECT * FROM items');
    res.json(items);
});

// Create a new item
app.post('/items', async (req, res) => {
    const db = await dbPromise;
    const { name } = req.body;

    if (!name) {
        return res.status(400).json({ error: 'Name is required' });
    }

    const result = await db.run('INSERT INTO items (name) VALUES (?)', [name]);
    const newItem = {
        id: result.stmt.lastID,
        name
    };

    res.status(201).json(newItem);
});

// Start the server
app.listen(port, () => {
    console.log(`Server is running on port ${port}`);
});
