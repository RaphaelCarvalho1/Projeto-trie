import asyncio
from websockets.server import serve

async def handle(websocket):
    async for message in websocket:
        await websocket.send("Server to client")
        print(message)   

async def main():
    async with serve(handle, "localhost", 8765):
        await asyncio.Future()  # run forever

asyncio.run(main())