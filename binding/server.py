import asyncio
from websockets.server import serve
import json
from trieBD import TrieBD

dataBase = TrieBD()

async def handle(websocket):
    async for message in websocket:
        #await websocket.send("Server to client")

        msg = json.loads(message);

        print(msg)

        dataBase.printAccount(msg["origin"])

        if(msg["type"] == "t"):
            dataBase.transact(msg["origin"], msg["destiny"], msg["amount"])

        if(msg["type"] == "r"):
            response = dataBase.getReport(msg["origin"], msg["destiny"])

            await websocket.send(response)

async def main():
    async with serve(handle, "localhost", 8765):
        await asyncio.Future()  # run forever

asyncio.run(main())