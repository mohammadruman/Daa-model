const express = require('express');
const app = express();
const port = process.env.PORT || 3000;

// Serve static files from a directory (e.g., HTML, CSS, JavaScript)
app.use(express.static(__dirname + '/public'));

app.get('/', (req, res) => {
  // You can send an HTML file as the response
  res.sendFile(__dirname + '/index.html');
});
app.get('/', (req, res) => {
    // You can send an HTML file as the response
    res.sendFile(__dirname + '/login.html');
  });

app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});
