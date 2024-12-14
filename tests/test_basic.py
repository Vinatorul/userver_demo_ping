import pytest

from testsuite.databases import pgsql


# Start the tests via `make test-debug` or `make test-release`

async def test_ping(service_client):
    response = await service_client.post(
        '/v1/ping',
        params={'name': 'user-from-initial_data.sql'},
    )
    assert response.status == 200
    assert response.text == 'Hi again, user-from-initial_data.sql!\n'
