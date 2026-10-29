import {test} from 'node:test';
import assert from 'node:assert/strict';
import {createGroundSampler} from '../ground.js';
test('ground height respects triangle boundaries, slopes, floors and step limits', () => {
  const ground = createGroundSampler(new Float32Array([
    0,0,0, 4,0,0, 0,0,4,
    0,3,0, 4,3,0, 0,3,4,
    4,0,0, 8,1,0, 4,0,4,
    10,0,0, 10,5,0, 10,0,5,
  ]), 3);
  assert.equal(ground(1,1), 3);
  assert.equal(ground(1,1, .45, -1), 0);
  assert.equal(ground(1,1, 2, .5), null);
  assert.equal(ground(3,3), null);
  assert.equal(ground(5,1), .25);
  assert.equal(ground(10,1), null);
  assert.equal(ground(-1,-1), null);
  assert.deepEqual(ground.pickRay([1,10,1],[0,-1,0]),[1,3,1]);
  assert.deepEqual(ground.pickRay([5,10,1],[0,-1,0]),[5,.25,1]);
  assert.equal(ground.pickRay([3,10,3],[0,-1,0]),null);
  assert.equal(ground.pickRay([1,10,1],[0,1,0]),null);
  assert.equal(ground.pickRay([1,10,1],[1,0,0]),null);
});
