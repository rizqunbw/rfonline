# RF Online browser prototype

The application and original uploaded assets are in [Platform01](Platform01/README.md).

Vercel can deploy from either repository root or `Platform01`. Keep Framework Preset **Other** and let the checked-in `vercel.json` select the build and output directory. From repository root, `npm run build` produces `Platform01/dist`; from the `Platform01` root it produces `dist`. Clear conflicting dashboard build/output overrides if present.
