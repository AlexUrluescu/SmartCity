import express from "express";

const app = express();
const PORT = 3001;

const data = [];

app.get("/data", (req, res) => {
  res.json(data);
});

app.get("/api/sendData", function (req, res) {
  const temperature = req.query.temperature;
  const humidity = req.query.humidity;
  const id = req.query.id;

  const dataReceived = {
    temperature: temperature,
    humidity: humidity,
    id: id,
  };

  data.push(dataReceived);

  res.json(dataReceived);
});

app.listen(PORT, () => {
  console.log(`Server is running at PORT ${PORT}`);
});
